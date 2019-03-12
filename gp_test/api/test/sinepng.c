#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gnuplot_i.h"

int main(int argc, char * argv[])
{
	gnuplot_ctrl * g = gnuplot_init();

//	gnuplot_cmd(g, "set terminal png");
//	gnuplot_cmd(g, "set output \"sine.png\"");
//	gnuplot_plot_equation(g, "sin(x)", "Sine wave");

	gnuplot_cmd(g, "set terminal png");
	gnuplot_cmd(g, "set output \"out_bin.png\"");

	gnuplot_cmd(g, "plot \"out.bin\" binary format=\"%%int\" u :1 with lines linestyle 2");
	gnuplot_cmd(g, "set grid");
	gnuplot_cmd(g, "set title \"from gnuplot api\"");
	gnuplot_cmd(g, "set xlabel \"x\"");
	gnuplot_cmd(g, "set ylabel \"x\"");

	gnuplot_close(g);

	return 0 ;
}

