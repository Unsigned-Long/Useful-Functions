import numpy as np
from matplotlib import pyplot as plt
import matplotlib.ticker as mtick
from mpl_toolkits.axes_grid1 import host_subplot

config = {
    # "text.usetex": True,
    "font.family": 'Ubuntu Mono',  # sans-serif/serif/cursive/fantasy/monospace
    "font.size": 14.0,  # medium/large/small
    'font.style': 'italic',  # normal/italic/oblique
    'font.weight': 'normal',  # bold
    "mathtext.fontset": 'cm',
    "font.serif": ['cmb10'],
    "axes.unicode_minus": False,
    'figure.figsize': (12.0, 4.0)
}

plt.rcParams.update(config)


class drawer:

    @staticmethod
    def show_figure(save_path=None):
        plt.tight_layout()
        if save_path is not None:
            plt.savefig(save_path)
        plt.show()

    @staticmethod
    def math_symbols(s: str):
        return r'$' + s + '$'

    @staticmethod
    def set_xticks(ax, xmin, xmax, tick_count):
        ax.set_xticks(np.arange(xmin, xmax + 1E-10, (xmax - xmin) / tick_count))
        ax.set_xlim(xmin, xmax)

    @staticmethod
    def set_yticks(ax, ymin, ymax, tick_count):
        ax.set_yticks(np.arange(ymin, ymax + 1E-10, (ymax - ymin) / tick_count))
        ax.set_ylim(ymin, ymax)

    @staticmethod
    def add_grids(ax, alpha=0.5):
        ax.grid(ls='-.', alpha=alpha)

    @staticmethod
    def set_label_decimal(ax, format_str, axis='y'):
        if axis == 'y':
            ax.yaxis.set_major_formatter(mtick.FormatStrFormatter(format_str))
        elif axis == 'x':
            ax.xaxis.set_major_formatter(mtick.FormatStrFormatter(format_str))

    @staticmethod
    def set_legend_top(ax, cols):
        ax.legend(bbox_to_anchor=(0.0, 1.05, 1.0, 0.0), loc=3, ncol=cols, mode="expand", borderaxespad=0.0)

    @staticmethod
    def get_cmap(color_name, len, start=0.0, end=1.0):
        """
        Perceptually Uniform Sequential:
        ['viridis', 'plasma', 'inferno', 'magma', 'cividis']

        Sequential:
        ['Greys', 'Purples', 'Blues', 'Greens', 'Oranges', 'Reds', 'YlOrBr', 'YlOrRd', 'OrRd', 'PuRd', 'RdPu', 'BuPu',
         'GnBu', 'PuBu', 'YlGnBu', 'PuBuGn', 'BuGn', 'YlGn']

        Sequential(2):
        ['binary', 'gist_yarg', 'gist_gray', 'gray', 'bone', 'pink', 'spring', 'summer', 'autumn', 'winter', 'cool',
         'Wistia', 'hot', 'afmhot', 'gist_heat', 'copper']

        Diverging:
        ['PiYG', 'PRGn', 'BrBG', 'PuOr', 'RdGy', 'RdBu', 'RdYlBu', 'RdYlGn', 'Spectral', 'coolwarm', 'bwr', 'seismic']

        Cyclic:
        ['twilight', 'twilight_shifted', 'hsv']

        Qualitative:
        ['Pastel1', 'Pastel2', 'Paired', 'Accent', 'Dark2', 'Set1', 'Set2', 'Set3', 'tab10', 'tab20', 'tab20b', 'tab20c']

        Miscellaneous：
        ['flag', 'prism', 'ocean', 'gist_earth', 'terrain', 'gist_stern', 'gnuplot', 'gnuplot2', 'CMRmap',
         'cubehelix', 'brg', 'gist_rainbow', 'rainbow', 'jet', 'turbo', 'nipy_spectral', 'gist_ncar']
        """

        return plt.get_cmap(color_name)(np.linspace(start, end, len))

    @staticmethod
    def set_sci_label(ax, axis='y'):
        ax.ticklabel_format(style='sci', scilimits=(0, 0), axis=axis)

    @staticmethod
    def use_style(idx=0):
        styles = ['default', 'classic'] + sorted(
            style for style in plt.style.available if style != 'classic' and not style.startswith('_')
        )
        plt.style.use(styles[idx])

    @staticmethod
    def set_axis_label_color(ax, color, axis='y'):
        if axis == 'y':
            ax.yaxis.get_label().set_color(color)
            # ax.yaxis.get_ticks().set_color(color)
            ax.tick_params(axis, colors=color)
        elif axis == 'x':
            ax.xaxis.get_label().set_color(color)


if __name__ == '__main__':
    # plt.rcParams['figure.figsize'] = (12.0, 4.0)

    host = host_subplot(121)

    twin = host.twinx()

    # fig, axs = plt.subplots(nrows=1, ncols=2, sharex='all', sharey='all')
    t = np.arange(0.0, 1.0 + 0.01, 0.01)
    s = np.sin(4 * np.pi * t)
    tan = np.tan(4 * np.pi * t)

    colors = drawer.get_cmap('plasma', 2, 0.3, 0.8)

    sin_plot, = host.plot(t, s, label=drawer.math_symbols('y=sin(4\pi t)'), color=colors[0])
    tan_plot, = twin.plot(t, tan, label=drawer.math_symbols('y=tan(4\pi t)'), c=colors[1])

    host.set_xlabel('t' + drawer.math_symbols('(s)'))
    host.set_ylabel('y' + drawer.math_symbols('(m)'))
    twin.set_ylabel('y' + drawer.math_symbols('(m)'))

    drawer.set_xticks(host, 0.0, 1.0, 8)
    drawer.set_yticks(host, -2.0, 2.0, 5)
    drawer.set_yticks(twin, -20.0, 20.0, 5)

    drawer.add_grids(host)

    drawer.set_axis_label_color(host, sin_plot.get_color())
    drawer.set_axis_label_color(twin, tan_plot.get_color())

    # drawer.set_sci_label(axs[0])
    drawer.set_label_decimal(host, '%.1f', axis='x')

    drawer.set_legend_top(host, 2)
    drawer.show_figure()
