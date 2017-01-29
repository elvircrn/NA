// linear interp sin
//x1 = linspace(0, 2 * %pi, 10);
//[y] = interp1(x1, sin(x1), linspace(0, 2 * %pi, 50));
//subplot(2, 2, 1);
//plot(linspace(0, 2 * %pi, 50), y, 'g*');
//plot(linspace(0, 2 * %pi, 50), sin);

function [r]= Runge(param)
    r = 1 ./ (1 + 25 * (param. ^2));
endfunction

function interpFunction(f)
    x1 = linspace(0, 2 * %pi, 10);
    [y] = interp1(x1, f(x1), linspace(0, 2 * %pi, 50));
    subplot(2, 2, 1);
    plot(linspace(0, 2 * %pi, 50), y);
endfunction

subplot(2, 2, 1);
interpFunction(sin);

subplot(2, 2, 2);
interpFunction(Runge);
