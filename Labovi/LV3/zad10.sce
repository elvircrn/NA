// Predavanje 3; Stranica 11

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

AA = [-2, -1, 3; 2, 6, 8; 6, 8, 18];
BB = [10, 3, 5];

//[res] = lijevo(AA, BB);
//disp(res);


//Mat = [9, 2, 3; 4, 5, 6; 7, 8, 9];
//disp(det(Mat));

//AA = [-2, -1, 3; 2, 6, 8; 6, 8, 18];

disp (inv(AA));


