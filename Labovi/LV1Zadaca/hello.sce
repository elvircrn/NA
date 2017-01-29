function plotFunction(fString)
    x = linspace(-200, 200, 100);
    deff('y = f(x)','y = ' + fString);
    plot(x, f);
endfunction

plotFunction('x * x * x');
