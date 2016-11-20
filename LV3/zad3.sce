xdata1 = linspace(0, 2 * %pi, 10);
ydata1 = sin(xdata1);
xx1 = linspace(0, 2 * %pi, 50);
= splin(xdata1, ydata1, "clamped", -cos(x));

res1 = splin(xdata1, ydata1, "not_a_knot");
[yy1] = interp(xx1, xdata1, ydata1, d);

subplot(2, 2, 1);
plot(x1, y1);




//subplot(2, 2, 2);


//subplot(2, 2, 3);
