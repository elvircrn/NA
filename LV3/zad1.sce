// a)
subplot(1, 2, 1);
x = linspace(0, 2 * %pi, 1000);
plot(x, sin);

// b)
function [y]= Runge(param)
    y = 1 ./ (1 + 25 * (param. ^2));
endfunction

//y2 = 1 ./ (1 + 25 * x. ^2); --> ovo je sa vektorom

subplot(1, 2, 2);
plot(linspace(-1, 1, 100), Runge);

