import numpy as np
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore
import pyqtgraph.opengl as gl
from matplotlib import cm

class RadarVisualizer:
    def __init__(self):
        pass

    @staticmethod
    def generate_range_profile_plot():
        figure = pg.plot(title='Range Profile')
        figure.showGrid(x=True, y=True)
        figure.setLabel('bottom', 'Range [m]')
        figure.setLabel('left', 'Relative Power [dB]')
        figure.addLegend()
        plots = [
            ('lime', 'Range Profile'),
            ('red', 'Noise Profile'),
        ]
        plot_objects = [[] for _ in range(len(plots))]

        for j, (color, name) in enumerate(plots):
            if name == 'TI - rangeBinIndexPhase':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('sandybrown')  # Red color for the symbol
                plot_obj = figure.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush,
                                       symbolSize=15, name=f'{name}')
            else:
                line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
                plot_obj = figure.plot(pen=line_style, name=f'{name}')
                plot_obj.setVisible(False)
            plot_objects[j].append(plot_obj)

        plot_objects[0][0].setVisible(True)
        plot_objects[1][0].setVisible(True)

        return figure, plot_objects

    @staticmethod
    def generate_heatmap_plot(title, x_label, y_label):
        """
        Generates a generic heatmap plot with specified labels and title.

        Parameters:
            title: str, the title of the heatmap plot
            x_label: str, label for the x-axis
            y_label: str, label for the y-axis

        Returns:
            heatmap_plot: pyqtgraph.PlotWidget, the plot widget for the heatmap
            heatmap_item: pyqtgraph.ImageItem, the heatmap image item
        """
        # Create a new plot window
        heatmap_plot = pg.plot(title=title)
        heatmap_plot.setLabel('bottom', x_label)
        heatmap_plot.setLabel('left', y_label)
        heatmap_plot.showGrid(x=True, y=True)

        # Create a heatmap image item
        heatmap_item = pg.ImageItem()
        heatmap_plot.addItem(heatmap_item)

        return heatmap_plot, heatmap_item

    @staticmethod
    def update_heatmap_plot(plot_item, heatmap_data, primary_axis, secondary_axis, apply_fftshift=False,
                            min_value=0, max_value=4096, colormap='jet'):
        """
        General-purpose function to update a heatmap plot with given data and axis ranges.

        Parameters:
            plot_item: pyqtgraph.ImageItem, the heatmap plot item to be updated
            heatmap_data: 2D numpy array, the data for the heatmap
            primary_axis: 1D array-like, values for the primary axis (x-axis)
            secondary_axis: 1D array-like, values for the secondary axis (y-axis)
            apply_fftshift: bool, whether to apply FFT shift on the secondary axis
            min_value: float, minimum value for normalization (default is heatmap_data.min())
            max_value: float, maximum value for normalization (default is heatmap_data.max())
            colormap: str, name of the matplotlib colormap to use (default is 'jet')
        """
        if plot_item is not None:
            # Apply FFT shift if the flag is enabled
            if apply_fftshift:
                heatmap_data = np.fft.fftshift(heatmap_data, axes=1)  # Shift along the secondary axis

            # Normalize data using the specified global minimum and maximum values
            heatmap_data_normalized = (heatmap_data - min_value) / (max_value - min_value)

            # Create a colormap lookup table
            cmap = cm.get_cmap(colormap)
            lookup_table = (cmap(np.linspace(0, 1, 256)) * 255).astype(np.uint8)

            # Apply the lookup table to the plot item
            plot_item.setLookupTable(lookup_table[:, :3])  # Use RGB channels only (ignore alpha)

            # Set the image data for the heatmap
            plot_item.setImage(heatmap_data_normalized)

            # Set fixed range for heatmap (prevents auto-scaling)
            plot_item.setLevels([0, 1])  # Set the color range to [0, 1]

            # Map the heatmap pixel indices to the primary and secondary axes
            plot_item.setRect(
                primary_axis[0], secondary_axis[0],  # Starting points for primary and secondary axes
                primary_axis[-1] - primary_axis[0], secondary_axis[-1] - secondary_axis[0]
                # Width and height of the map
            )

    @staticmethod
    def update_range_profile_plot(range_profile_plot_objects, x1, y1, x2, y2):
        """
        Updates range profile plots with the given data.

        Parameters:
            x1: float, the length of the x-axis for the first plot. Set to 0 to auto-scale.
            y1: 1D array-like, the data for the first plot.
            x2: float, the length of the x-axis for the second plot. Set to 0 to auto-scale.
            y2: 1D array-like, the data for the second plot.
        """
        len_y1 = len(y1)
        if x1 == 0:
            x1 = len_y1
        x_axis_y1 = np.linspace(0, x1, len_y1)

        len_y2 = len(y2)
        if x2 == 0:
            x2 = len_y2
        x_axis_y2 = np.linspace(0, x2, len_y2)
        if len_y1 > 0:
            range_profile_plot_objects[0][0].setData(x_axis_y1, np.abs(y1))
        if len_y2 > 0:
            range_profile_plot_objects[1][0].setData(x_axis_y2, np.abs(y2))

