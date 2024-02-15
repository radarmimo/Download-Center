# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# setup(name='pyneulog',
#     version='0.1',
#     install_requires=['pyserial'],
#     description="Python interface for Neulog GSR sensors",
#     author='Tristan Hearn',
#     author_email='tristanhearn@gmail.com',
#     url='https://github.com/thearn/pyneulog',
#     license='Apache 2.0',
#     packages=['neulog'],
# )


import serial
import time
import asyncio
from serial.tools.list_ports import comports

MAX_TYPE = 0x22
MAX_ID = 0x09
ACK = 0x0b
STX_4SAMP = 0x11
STX_USB = 0x12
USB_LEARN = 0x60
WRITE_TO_EE = 0x2d
START_SAMPLE = 0x2e
STOP_SAMPLE = 0x2f
IN_READ = 0x31
READ_PARAMETERS = 0x32
READ_RAM = 0x35
SEN_LIST = 0x47
EXP_SAMPLES = 0x49
EXP_TRIGGER = 0x4a
TX_4_EE = 0x4e
START_UPLOAD = 0x53
STX = 0x55
RESERVED_FOR_STX = 0x55
START_SAMPLE_GROUP = 0x56
FINISH_UPLOAD = 0x58

DEVICE_TYPES=['Temperature', 'Light', 'Voltage', 'Current', 'PH', 'Oxygen', 'PhotoGate', 'Pulse', 'Force', 'Sound',                     
'Humidity', 'Pressure', 'Motion', 'Magtnetic', 'Conductivity', 'GSR', 'CO2', 'Barometer', 'Rotary', 
'Acceleration', 'Spirometer', 'SoilMoisture', 'Turbidity', 'UVB', 'EKG', 'Colorimeter', 'DropCounter', 
'FlowRate', 'ForcePlate', 'BloodPressure', 'Salinity', 'UVA', 'SurfaceTemp', 'WideRangeTemp', 
'InfraredThermometer', 'Respiration', 'HandDynamometer', 'Calcium', 'Chloride', 'Ammonium', 'Nitrate', 
'Anemometer', 'GPS', 'Gyroscope', 'DewPoint', 'Charge']

def bcd(l):
    if [255, 255, 255] == l: return '-'
    num = ''
    for i in l:
        t = i // 16
        if 10 == t: t = '.'
        elif 11 == t: t = '+'
        elif 12 == t: t = '-'
        elif 13 == t: t = ' '
        else: t = str(t)
        num = num + t
        t = i % 16
        if 10 == t: t = '.'
        elif 11 == t: t = '+'
        elif 12 == t: t = '-'
        elif 13 == t: t = ' '
        else: t = str(t)
        num = num + t
    return num.strip()

class Device(serial.Serial):
    def __init__(self, port = None):
        if not port:
            port = self.get_port()
        serial.Serial.__init__(
            self,
            port = port,
            baudrate = 115200,
            parity = serial.PARITY_NONE,
            stopbits = serial.STOPBITS_TWO,
            bytesize = serial.EIGHTBITS,
            timeout = 1
        )
        self.status = 'connected'
        self.buf = []

    def get_port(self):
        return detect_device()
        """
        osname = platform.system()
        if osname == "Darwin":
            port = "/dev/tty.SLAB_USBtoUART"
        else:
            port = "COM5"
        """

    def send(self, s, checksum = False):
        time.sleep(0.01)
        if checksum:
            s += bytes([sum(s)%256])
        self.write(s)
        self.flush()

    def receive(self, i = False):
        time.sleep(0.01)
        iw = self.inWaiting()
        if False == i: i = iw
        if iw >= i:
            #print "reading %i out of %i" % (i, iw)
            r = self.read(i)
            return r
        return False

    async def receiveAio(self, i = False):
        await asyncio.sleep(0.01)
        iw = self.inWaiting()
        if False == i: i = iw
        if iw >= i:
            #print "reading %i out of %i" % (i, iw)
            r = self.read(i)
            return r
        return False

    def connect(self):
        self.close()
        self.open()
        self.send(bytes([STX]) + b'NeuLog!')
        if b'OK-V' != self.receive(4): 
            return False
        self.status = 'connected'
        return '.'.join([str(c) for c in self.receive(3)])

    def scanStart(self):
        if self.status != 'connected': return False
        self.send(bytes([STX_USB, USB_LEARN, MAX_TYPE, MAX_ID]), True)
        r = self.receive(4)
        print("What's this: %i" % (r[-1]))
        if bytes([STX_USB, USB_LEARN, ACK]) == r[:-1]:
            self.status = 'scanning'
            return True
        return False

    def scanRead(self):
        if self.status != 'scanning': return False
        sensors = []
        r = self.receive()
        while len(r) > 7:
            chunk, r = r[:8], r[8:]
            if STX != chunk[0]: continue
            chunk = [c for c in chunk]
            if chunk[-1] != sum(chunk[:-1]) % 256: continue
            stype, sid, ssndver = chunk[1:4]
            sver = '.'.join([str(i) for i in chunk[4:7]])
            sensors.append((stype, sid, sver))
        return sensors

    def scanStop(self):
        if self.status != 'scanning': return False
        self.send(bytes([STX_USB]))
        self.receive()
        self.status = 'connected'
        return True

    def eeread(self, stype, sid, add):
        if self.status[:7] == 'running': return False
        self.send(bytes([STX, stype, sid, READ_PARAMETERS, 0, add, 0]), True)
        t = self.receive()
        if t[0:4] != bytes([STX, stype, sid, READ_PARAMETERS]):
            #FIXME This sometimes returns nothing
            print('Did not get response from eeread, will keep on trying')
            return self.eeread(stype, sid, add)
            raise Exception('Sensor did not acknowledge');
        return [c for c in t[4:7]]

    def eewrite(self, stype, sid, add, val):
        if self.status[:7] == 'running': return False
        self.send(bytes([STX, stype, sid, WRITE_TO_EE, 0, add, val]), True)
        if self.receive()[0:5] != bytes([STX, stype, sid, WRITE_TO_EE, ACK]):
            raise Exception('Sensor did not acknowledge');

    def getSensorRange(self, stype, sid):
        if self.status != 'connected': return False
        return self.eeread(chr(stype), chr(sid), chr(11))[0];

    def setSensorRange(self, stype, sid, val):
        if self.status != 'connected': return False
        self.eewrite(chr(stype), chr(sid), chr(11), chr(val))
        return True

    def getSensorsData(self, stype, sid):
        if self.status != 'connected': return False
        if isinstance(stype, str):
            stype = DEVICE_TYPES.index(stype) + 1
        self.send(bytes([STX, stype, sid, IN_READ, 0, 0, 0]), True)
        r = self.receive()
        if not r or STX != r[0] or len(r) < 4 or IN_READ != r[3]: return False
        if r[-1] != sum(r[:-1]) % 256: return False
        return bcd(r[4:7])

    async def getSensorsDataAio(self, stype, sid):
        if self.status != 'connected': return False
        if isinstance(stype, str):
            stype = DEVICE_TYPES.index(stype) + 1
        self.send(bytes([STX, stype, sid, IN_READ, 0, 0, 0]), True)
        r = await self.receiveAio()
        if not r or STX != r[0] or IN_READ != r[3]: return False
        if r[-1] != sum(r[:-1]) % 256: return False
        return bcd(r[4:7])

    def expStart(self, rate, timebase, samples, sensors, online):
        if self.status != 'connected': return False
        self.status = 'preparing'
        self.send(bytes([STX, 0, 0, STOP_SAMPLE, 0, 0, 0]), True)

        if 2 == timebase: fast = 1
        else: fast = 0

        # Get params from first sensor
        if not online:
            s = sensors[0]
            stype = chr(s[0])
            sid = chr(s[1])

            d = self.eeread(stype, sid, chr(72))
            rate = d[0] * 256 + d[1]
            if 0 == d[2]:
                rate *= 0.01
            elif 2 == d[2]:
                rate *= 0.0001

            d = self.eeread(stype, sid, chr(79))
            samples = d[0] * 256 + d[1]

        # Sensors, like many other things in NeuLog, are enumerated from 1
        i = 1
        for s in sensors:
            stype = chr(s[0]);
            sid = chr(s[1]);

            # Sensor list
            self.send(bytes([STX_USB, SEN_LIST, i, stype, sid, 1]), True)
            if self.receive()[0:4] != bytes([STX_USB, SEN_LIST, i, ACK]):
                raise Exception('Sensor did not acknowledge');
            i += 1

            # Mark sensor as participant
            self.eewrite(stype, sid, chr(14), chr(1))

            # Sensor options
            if online:
                self.eewrite(stype, sid, chr(2), chr(rate // 256))
                self.eewrite(stype, sid, chr(3), chr(rate % 256))
                self.eewrite(stype, sid, chr(4), chr(timebase))
                self.eewrite(stype, sid, chr(5), chr(0))
                self.eewrite(stype, sid, chr(6), chr(0))
                self.eewrite(stype, sid, chr(7), chr(0))
                self.eewrite(stype, sid, chr(8), chr(0))
                self.eewrite(stype, sid, chr(9), chr(samples // 256))
                self.eewrite(stype, sid, chr(10), chr(samples % 256))
                self.eewrite(stype, sid, chr(12), chr(fast))

        self.send(bytes([STX_USB, EXP_SAMPLES, samples // 256, samples % 256]), True)
        if self.receive()[0:3] != bytes([STX_USB, EXP_SAMPLES, ACK]):
            raise Exception('Sensor did not acknowledge');

        if online:
            self.send(bytes([STX_USB, EXP_TRIGGER] + [0] * 7), True)
            if self.receive()[0:3] != bytes([STX_USB, EXP_TRIGGER, ACK]):
                raise Exception('Sensor did not acknowledge');
            self.send(bytes([STX_USB, START_SAMPLE]), True)
            if self.receive(4)[0:3] != bytes([STX_USB, START_SAMPLE, ACK]):
                raise Exception('Sensor did not acknowledge');
            self.status = 'runningOnline'
        else:
            self.send(bytes([STX_USB, START_UPLOAD]), True)
            if self.receive(4)[0:3] != bytes([STX_USB, START_UPLOAD, ACK]):
                raise Exception('Sensor did not acknowledge');
            self.status = 'runningOffline'

        return True

    def expStop(self):
        if self.status[:7] != 'running': return False
        self.send(bytes([STX, 0, 0, STOP_SAMPLE, 0, 0, 0]), True)
        self.status = 'connected'
        return True

    def getSamples(self):
        if self.status[:7] != 'running': return False
        samples = []
        updates = []
        self.buf += self.receive()

        if len(self.buf) > 3 and self.buf[0] == STX_USB:
            if self.buf[1] in [STOP_SAMPLE, FINISH_UPLOAD] and self.buf[2] == ACK:
                self.status = 'connected'
                samples.append('done')
            else:
                print('USB said: ', self.buf)
            self.buf = self.buf[4:]

        while len(self.buf) > 18 and len(samples) < 100:
            if self.buf[0] == STX_4SAMP and self.buf[3] == TX_4_EE:
                stype = self.buf[1]
                sid = self.buf[2]
                dat = [bcd([c for c in self.buf[i:i+3]]) for i in range(6, 16, 3)]
                samples.append([stype, sid, dat])

                self.buf = self.buf[19:]
            elif self.buf[0] == STX and self.buf[3] == READ_RAM:
                stype = self.buf[1]
                sid = self.buf[2]
                dat = bcd([c for c in self.buf[4:7]])
                updates.append([stype, sid, dat])
                self.buf = self.buf[8:]
            else:
                print("!!LOST %i" % (self.buf[0]))
                self.buf = self.buf[1:]

        return [samples, updates]

def detect_device():
    for ser in comports():
        d = Device(port=ser.device)
        try:
            if d.connect():
                return d
        except:
            pass
    return None

if __name__ == '__main__':
    d = detect_device()
    print(d.connect())
    start = time.time()
    cnt = 0
    while True:
        v = d.getSensorsData('Respiration', 1)
        print(' ' * 20, end='\r')
        print(v, end='\r', flush=True)
        cnt += 1
        if time.time() - start >= 10:
            break
    print(cnt / 10)