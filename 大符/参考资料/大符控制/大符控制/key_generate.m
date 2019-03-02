okstatus = 0;
for i=1:100
    for j=1:5
        okstatus = 0;
        while(okstatus==0)
            a(i,j) = unidrnd(9);
            for k=1:j
                if(a(i,k) == a(i,j))
                    break;
                end
            end
            if(k==j) 
                okstatus=1;
            end
        end
    end
end

for i = 1:100
    for j=1:5
        num( (i-1)*5+j ) = a(i,j);
    end
end
num = num';
csvwrite('key_forSTM32.csv',num); %写进控制程序的一维数组
csvwrite('key_fortest.csv',a); %二维数组，方便视觉检查
            