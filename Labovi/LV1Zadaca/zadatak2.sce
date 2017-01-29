function plotFunction(fString)
    deff('[z] = f(x, y)','z = ' + fString);
    x = linspace(-4, 4, 100);
    y = linspace(-4, 4, 100);
    z = feval(x, y, f);
    surf(x, y, z);
endfunction

plotFunction('x^2 + y^2');
