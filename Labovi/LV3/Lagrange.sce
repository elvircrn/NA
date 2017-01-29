function s = LaGrange(xdata, ydata1, x)
    s = 0;
    n = size(xdata1, 2);
    for i = 1:n
        p = ydata1(i);
        if (ydata1(i) == 0)
            p = 0;
        for j = 1:n
            if j <> i then
                p = p * (x - xdata1(j)) / (xdata1(i) - xdata1(j));
            end
        end
        s = s + p;
    end
    return s;
endfunction



xdata1 = linspace(0, 2 * %pi, 50);
[y] = LaGrange(xdata1, sin(xdata1), %pi);

disp(y);



    
