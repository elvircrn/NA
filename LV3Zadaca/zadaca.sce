function [y] = LaGrange(xdata,ydata,x)
    xn = size(x, 2);
    xdatan = size(xdata, 2);
    y = zeros(1, xn);
    for i = 1:xdatan
        if ydata(i) == 0
            continue;
        end
        p = zeros(1, xn);
        p(1, 1:xn)=p(1, 1:xn) + ydata(i);
        for j = 1:xdatan
            if (i <> j)
               p(1, 1:xn) = p(1, 1:xn). * ((x(1, 1:xn) - xdata(j)) / (xdata(i) - xdata(j)));
            end
        end
        y = y + p;
    end
endfunction

function [r]= Runge(param)
    r = 1 ./ (1 + 25 * (param. ^2));
endfunction

function [y] = f1(x)
    
endfunction


function [y] = sigmoid(x)
    e = %e^-x;
    y = 1 / (1 + e);
endfunction

function interpFunction(f, odakle, dokle, kolko_seed, kolko_gen)
    x1 = linspace(odakle, dokle, kolko_seed);
    [y] = LaGrange(x1, f(x1), linspace(odakle, dokle, kolko_gen));
    plot(linspace(odakle, dokle, kolko_gen), y);
endfunction

subplot(3, 2, 1);
interpFunction(sin, -%pi * 2, 2 * %pi, 50, 50);

subplot(3, 2, 2);
interpFunction(Runge, -1, 1, 10, 50);

subplot(3, 2, 3);
interpFunction(atan, -10, 10, 10, 50);

subplot(3, 2, 4);
interpFunction(tanh, -10, 10, 10, 50);


subplot(3, 2, 5);
interpFunction(acos, -10, 10, 10, 50);
