#include "usrprx.h"

usrpRx::usrpRx(QObject *parent)
    : QThread{parent}
{

}



void usrpRx::run()
{
//    std::cout << "Thread started.\n";
//    bool sweepMode = true;

    std::string device_args("type=b200");

    uhd::device_addrs_t device_addrs = uhd::device::find(device_args);
//    std::cout << std::endl;
//    std::cout << boost::format("Creating the usrp device with: %s...") % device_args << std::endl;
//    std::cout << "device address : " << device_addrs.data() << std::endl;

    if (device_addrs.data() == 0) {
        emit usrpStatus(false, " ");
        return;
    }
    usrp = uhd::usrp::multi_usrp::make(device_args);

    std::string subdev("A:A");
//    std::string subdev("A:A A:B");

//    usrp->set_rx_dc_offset(true);
    std::string ant("TX/RX");

//    std::string ref("internal");

//    double rate(56e6);
//    int mSamples(1040);
    //    double freq(2.45e9);
    //    double gain(60);
    //    double bw(50e6);

//    std::cout << usrp->get_rx_dc_offset_range(0).to_pp_string() << std::endl;
    usrp->set_rx_subdev_spec(subdev);
    usrp->set_rx_rate(rate);
//    usrp->set_rx_freq(freq);
//    usrp->set_rx_freq(freq,1);
    usrp->set_rx_bandwidth(rate);
    usrp->set_rx_gain(gain);
    usrp->set_rx_antenna(ant);
    usrp->set_rx_agc(agc);


    emit usrpStatus(true, QString::fromStdString(device_addrs.data()->to_string().c_str()));
    // start Rx
    uhd::rx_streamer::sptr rx_stream;
    uhd::rx_metadata_t md;
    usrp->set_time_now(uhd::time_spec_t(0.0));
    std::string wire;
    std::vector<size_t> channel_nums(0);
    uhd::stream_args_t stream_args("fc32"); // complex float
    stream_args.channels             = channel_nums;
    stream_args.args["spp"] = "2040"; //  samples per packet (buffer size, which saves samples if we could not receive on-time)
    rx_stream = usrp->get_rx_stream(stream_args);

    std::cout << "name = " << usrp->get_rx_subdev_spec().to_pp_string() << std::endl;
    double seconds_in_future(1.5);
//    int nSamples = mSamples * 2 * 10;
    size_t total_num_samps(mSamples*2*nTimeFrame);
    uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
    stream_cmd.num_samps  = total_num_samps;
    stream_cmd.stream_now = false;
    stream_cmd.time_spec  = uhd::time_spec_t(seconds_in_future);
    rx_stream->issue_stream_cmd(stream_cmd);

    std::vector<std::complex<float>> buff(rx_stream->get_max_num_samps());

//    std::cout << rx_stream->get_max_num_samps() << std::endl;
//    std::cout << buff.size() << std::endl;
    double timeout = seconds_in_future + 0.1; // timeout (delay before receive + padding)
     // number of accumulated samples

    int sCounter = 0;

    while (true) {
        QVector<double> dataI, dataQ;
        total_num_samps = mSamples*2*nTimeFrame;

        size_t num_acc_samps = 0;

        usrp->set_rx_freq(sweepArrayFreqMHz[sCounter]*1e6);

//        if (sweepArrayAnt[sCounter] == 0) {
//            ant = "TX/RX";
//        }
//        else{
//            ant = "RX2";
//        }


//        usrp->set_rx_antenna(ant);

        double freq1 = usrp->get_rx_freq();

        while (num_acc_samps < total_num_samps) {
            // receive a single packet
            size_t num_rx_samps = rx_stream->recv(&buff.front(), buff.size(), md, timeout, true);
            timeout = 0.1;

            if (buff.at(0).real() == 0 && buff.at(0).imag() == 0
                    && buff.at(1).real() == 0 && buff.at(1).imag() == 0) {
                continue;
            }

            for (int i = 0; i < mSamples; ++i) {
                dataI.push_back(buff.at(i).real());
                dataQ.push_back(buff.at(i).imag());
            }

            num_acc_samps += num_rx_samps;


        }
        double freq2 = usrp->get_rx_freq();
        if (std::abs(freq1-freq2) < 1) {
            dataI.push_back(freq2/1e6);
//            dataI.push_back(sweepArrayRF[sCounter]);
            dataQ.push_back(sCounter);
//            dataQ.push_back(RFB);
            emit dataReady(dataI, dataQ);
        }


        sCounter++;

        if (sCounter >= sweepArrayFreqMHz.size() ) {
            sCounter = 0;
        }


    }
}






