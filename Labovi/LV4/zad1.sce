xdata = linspace(0, 2 * %pi, 10);
ydata = sin(xdata);
x = linspace(0, 2 * %pi, 100);
d = splin(xdata, ydata);
[yp, yp1, yp2] = interp(x, xdata, ydata, spin(xdata, ydata));
subplot(121);
plot(x, yp1, 'k');
plot(x, yp2, 'r');

// 


xdata = linspace(0, 2 * %pi, 10);
ydata = sin(xdata);
x = linspace(0, 2 * %pi, 100);
d = splin(xdata, ydata);
[yp, yp1, yp2] = interp(x, xdata, ydata, spin(xdata, ydata));
subplot(121);
plot(x, yp1, 'k');
plot(x, yp2, 'r');

// 
p = poly([5, 1, 2, 1], 'x', 'c');
y = poly(0, 'y');
q = 1 / y^2 + 1;
pp1 = derivat(p);
pp2 = derivat(pp2);

//
function [y] = myFun(x)
    y = sum(x.^3);
endfunction
x = [1; 2; 3];
[J, H] = numderivative(myFun, x, [], [], "blockmat");

//
function f = fun(x, a, b, c)
    f = (x + a) ^c + b;
endfunction
a = 3;
b = 4;
c = 2;
x = 1;

g = numderivative(list(fun a, b, c, ), x);

exact = c * (x + a) ^(c - 1);


// zadatak 5
x = integrate('sin(t)', 't', 0, 0:0.5:%pi);



// zadatak 6
function f = fun(x)
    f = x * sin(30 * x) / sqrt (1 - (x / (2 * %pi))^2)
endfunction

x=intg(0, 2 * %pi, f);

// zadatak 7
function [y] = g(z)
    z = y^(3 + %i * %pi);
endfunction



I = intc(%i, 4 - %i, g);

// zadatak 8
x1 = linspace(0, %pi, 0.5);
I = inttrap(x1, cos(x1));
I = intsplin(x1, cos(x1));

// zadatak 9 

