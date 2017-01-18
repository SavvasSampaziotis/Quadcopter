function [ dZ ] = filteredSystem( t, Z, T, A, Ad, F );
%FILTEREDSYSTEM Υλοποίηση του φιλτραρισμένου γραμμικά παραμετροποιημένου
%συστήματος του εκρεμμους. Το Ζ αποτελεί το διάνυσμα οπισθοδρομητή
l1 = 3; l2 = 6;
L1 = l1*l2;
L2 = l1+l2;

i = getIndex(T, t);
a = A(i);
ad = Ad(i);
f = F(i);

dZ1 = Z(2);
dZ2 = -L1*Z(1) - L2*Z(2) - sin(a);
dZ3 = Z(4);
dZ4 = -L1*Z(3) - L2*Z(4) + f;
dZ5 = Z(6);
dZ6 = -L1*Z(5) - L2*Z(6)  + a*L1 + ad*L2;
dZ = [dZ1;dZ2;dZ3;dZ4;dZ5;dZ6];

end

function i = getIndex(T, t)
    for i=1:1:length(T);
       if t >= T(i) % found closest t at index i
           break;
       end
    end
end

