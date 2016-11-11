function plotFunction(fString)
    x = linspace(-2, 2, 100);
    deff('y = f(x)','y = ' + fString);
    plot(x, f, '*cya--');
    plot(x, f);
endfunction

plotFunction('sin(x)');
