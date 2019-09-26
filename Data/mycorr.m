GoldenFly = imread('GoldenFlyOutput.jpg');   
GoldenFly = reshape(GoldenFly,[],1);
GoldenGreatWall = imread('GoldenGreatwallOutput.jpg');
GoldenGreatWall = reshape(GoldenGreatWall,[],1);
GoldenSmall = imread('GoldenSmallOutput.jpg');
GoldenSmall = reshape(GoldenSmall,[],1);
pThreadFly = imread('pThreadFlyOutput.jpg'); 
pThreadFly = reshape(pThreadFly,[],1);
pThreadGreatWall = imread('pThreadGreatwallOutput.jpg'); 
pThreadGreatWall = reshape(pThreadGreatWall,[],1);
pThreadSmall = imread('pThreadSmallOutput.jpg'); 
pThreadSmall = reshape(pThreadSmall,[],1);
corr(double(GoldenGreatWall),double(pThreadGreatWall))
corr(double(GoldenFly),double(pThreadFly))
corr(double(GoldenSmall),double(pThreadSmall))




