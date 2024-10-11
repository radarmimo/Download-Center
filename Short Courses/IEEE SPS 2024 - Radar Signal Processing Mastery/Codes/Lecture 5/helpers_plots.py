import numpy as np
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.opengl as gl

ENABLE_RANGE_PROFILE_PLOT = True
ENABLE_3D_PLOT = True
min_range = 0
max_range = 60
num_rings = 6  # Number of concentric circles
num_angles = 12  # Number of radial lines
radius_interval = 10.0
ppi_opacity = 150  # Opacity of PPI grids (0-255)

# range_profile = []
def generate_range_profile_plot():
    # global object_distance_start_range, object_distance_stop_range
    plot = pg.plot(title='Range Profile')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Range [m]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('lime', 'Sum of Rx channels'),
        ('red', 'Real'),
        ('blue', 'Imaginary'),
        ('lightcoral', 'Selected Range Index'),
        ('sandybrown', 'TI - rangeBinIndexPhase')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    # for i in range(num_rx_antennas):
    for j, (color, name) in enumerate(plots):
        if name == 'TI - rangeBinIndexPhase':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('sandybrown')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=15,
                                 name=f'{name}')
        elif name == 'Selected Range Index':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('lightcoral')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=15,
                                 name=f'{name}')
        else:
            line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
            plot_obj = plot.plot(pen=line_style, name=f'{name}')
            plot_obj.setVisible(False)
        plot_objects[j].append(plot_obj)
    plot_objects[0][0].setVisible(True)
    # linear_region_range_profle = pg.LinearRegionItem([object_distance_start_range, object_distance_stop_range],
    #                                                  brush=(255, 255, 0, 20))  # Yellow color with opacity
    # plot.addItem(linear_region_range_profle)
    #
    # def region_changed():
    #     global object_distance_start_range, object_distance_stop_range
    #     region = linear_region_range_profle.getRegion()
    #     object_distance_start_range = region[0]
    #     object_distance_stop_range = region[1]
        # print("Linear Region Position:", region)

    # linear_region_range_profle.sigRegionChanged.connect(region_changed)

    return plot, plot_objects

if ENABLE_RANGE_PROFILE_PLOT:
    range_profile_figure, range_profile_plots = generate_range_profile_plot()
    range_profile_figure.show()

def generate_3d_plot():
    # app = pg.mkQApp()
    win = gl.GLViewWidget()
    win.setWindowTitle('3D Point Cloud')

    # Add coordinate axes
    ax = gl.GLAxisItem()
    win.addItem(ax)

    # Add grid
    grid = gl.GLGridItem()
    win.addItem(grid)

    # Initialize scatter plot item
    scatter = gl.GLScatterPlotItem()
    win.addItem(scatter)

    # Set view range and labels for 3D plot
    # Set view range for 3D plot (distance, elevation, azimuth)
    # win.opts['distance'] = 30
    # win.opts['elevation'] = 30
    # win.opts['azimuth'] = 30

    # Set view range for 3D plot
    win.opts['distance'] = 30

    # Set elevation (vertical angle) to look from above
    win.opts['elevation'] = 90  # 90 degrees looks directly down (top view)

    # Set azimuth (horizontal angle) to any angle you prefer
    win.opts['azimuth'] = 0  # 0 degrees points towards positive X-axis (default)

    # Add radar azimuth, elevation, and range coverages
    # radar_azimuth_coverage = gl.GLLinePlotItem(pos=np.array([[0, 0, 0], [max_range * np.cos(np.deg2rad(30)), max_range * np.sin(np.deg2rad(30)), 0]]), color=(255, 0, 0, 255))
    # win.addItem(radar_azimuth_coverage)
    #
    # radar_elevation_coverage = gl.GLLinePlotItem(pos=np.array([[0, 0, 0], [max_range * np.cos(np.deg2rad(30)), 0, max_range * np.sin(np.deg2rad(30))]]), color=(0, 255, 0, 255))
    # win.addItem(radar_elevation_coverage)
    #
    # radar_range_coverage = gl.GLLinePlotItem(pos=np.array([[0, 0, 0], [max_range, 0, 0]]), color=(0, 0, 255, 255))
    # win.addItem(radar_range_coverage)
    # Add PPI grids
    for i in range(num_rings):
        radius = radius_interval * (i + 1)
        theta = np.linspace(0, 2 * np.pi, 100)
        x = radius * np.cos(theta)
        y = radius * np.sin(theta)
        z = np.zeros_like(x)
        grid_item = gl.GLLinePlotItem(pos=np.vstack((x, y, z)).T, color=(255, 0, 255, ppi_opacity))
        win.addItem(grid_item)

    for i in range(num_angles ):
        theta = 2 * np.pi / num_angles  * i
        x = np.array([0, max_range * np.cos(theta)])
        y = np.array([0, max_range * np.sin(theta)])
        z = np.zeros_like(x)
        grid_item = gl.GLLinePlotItem(pos=np.vstack((x, y, z)).T, color=(255, 255, 0, ppi_opacity))
        win.addItem(grid_item)

    return win, scatter

if ENABLE_3D_PLOT:
    view_3d, scatter_3d = generate_3d_plot()
    view_3d.show()


def update_plots(range_profile, detected_points, noise_profile):
    len_range_profile = len(range_profile)
    len_noise_profile = len(noise_profile)

    if ENABLE_RANGE_PROFILE_PLOT and len_range_profile > 0:
        x_axis_range_profile = np.linspace(min_range, max_range, len_range_profile)
        x_axis_noise_profile = np.linspace(min_range, max_range, len_noise_profile)
        abs_range_profile = np.abs(range_profile)
        abs_noise_profile = np.abs(noise_profile)
        range_profile_plots[0][0].setData(x_axis_range_profile, abs_range_profile)
        range_profile_plots[1][0].setData(x_axis_noise_profile, abs_noise_profile)
        range_profile_plots[2][0].setData(x_axis_range_profile, np.imag(range_profile))

    if ENABLE_3D_PLOT:
        if detected_points:
            pos = np.array([[point['X'], point['Y'], point['Z']] for point in detected_points])
            # color = np.ones((len(pos), 4))  # White color for all points
            color = np.ones((len(pos), 4))  # Initialize with ones (white color with full opacity)
            color[:, 0] = 1.0  # Set red channel to 1 (full red)
            color[:, 1] = 0.0  # Set green channel to 0 (no green)
            color[:, 2] = 0.0  # Set blue channel to 0 (no blue)
            color[:, 3] = 1.0  # Set alpha channel to 1 (full opacity)
            size = np.ones(len(pos)) * 5  # Point size
            scatter_3d.setData(pos=pos, color=color, size=size)
        else:
            a = 1
            # Handle case where detected_points is empty or not yet populated
            # print("Detected points array is empty or not yet populated.")

    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~