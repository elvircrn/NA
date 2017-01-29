function [X] = lijevo(A, B)
    [n, ac] = size(A);
    [ac, m] = size(B);
    for k = 1:n
        for i = (k + 1):n
            mi = A(i, k) / A(k, k);
            A(i,k+1:n) = A(i,k+1:n) - mi * A(k, k+1:n);
            B(i,1:m) = B(i, 1:m) - mi * B(k, 1:m);
        end
    end
    X = zeros(n, m);
    for k = 1:m
        for i = n:-1:1
            s = B(i, k)
            for j = (i + 1):n
                s = s - A(i, j) * X(j, k);
            end
            X(i, k) = s / A(i, i);
        end
    end
endfunction

function [u] = polyfit(x, y, n)
    m = size(x,2);
    A = ones(m,n+1);
    y = y.';
    for i = 1:m
        for j = 2:n+1
            A(i,j) = A(i, j - 1) * x(i);
        end
    end
    u = pinv(A) * y;
endfunction


function [u] = polyfit2(x,y,n)
    m = size(x,2);
    A = ones(m,n+1);
    y = y.';
    for i = 1:m
            for j = 2:n+1
            A(i,j) = A(i,j-1) * x(i);
        end
    end
    u = lijevo(A.' * A, A.' * y);
endfunction

function [u] = polyfit3(x,y,n)
    m = size(x,2);
    A=ones(m,n+1);
    y=y.';
    for i = 1:m
        for j = 2:n+1
            A(i,j) = A(i,j-1) * x(i);
        end
    end
    [Q, R, E] = qr(A);
    u = R \ (Q.' * y);
    u = E * u;
endfunction

function [y] = polyval(u,x,n)
    m = size(x,2);
    y = zeros(1, m);
    for i = 1:n+1
        y(1, 1:m) = y(1, 1:m) + u(i) * x(1, 1:m) .^(i-1)
    end
endfunction

function [r]= runge(param)
    r = 1 ./ (1 + 25 * (param. ^2));
endfunction

function [y] = sigmoid(x)
    e = %e^-x;
    y = 1 / (1 + e);
endfunction


function doStuff(xmin, xmax, n_tacki, func, n_poli)    
    x = linspace(xmin, xmax, n_tacki);
    deff('[y]=f(x)', 'y=' + func);
    y = feval(x, f);
    u = polyfit3(x, y, n_poli);
    y2 = polyval(u, x, n_poli);
    plot(x, y);
    plot(x, y2, 'r');
endfunction

subplot(4, 4, 1)
doStuff(-5, 5, 100, 'sigmoid(x)', 10)

subplot(4, 4, 2)
doStuff(-2, 2, 20, 'runge(x)', 5)

subplot(4, 4, 3)
doStuff(-50, 50, 100, 'sin(x)', 10)

subplot(4, 4, 4)
doStuff(-5, 5, 100, 'atan(x)', 10)
