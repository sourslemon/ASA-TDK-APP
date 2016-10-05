%Step1. Image read
RGB = imread('test8.jpg');
figure(1)
imshow(RGB);

%Step2. Image binarization
I = rgb2gray(RGB);
    %灰階
threshold = graythresh(I); 
threshold = 0.6
    % Otsu's method to get a threshold that minimizes the intra-class variance
    % 大津演算法求閾值
bw = im2bw(I,threshold);
    % 依據閾值二值化
figure(2)
imshow(bw)
figure(3)

%Step3. Remove noise
%se = strel('disk',2);
%bw = imclose(bw,se);
    %imclose隙縫填滿，比較好分析
bw = bwareaopen(bw,300);
    %bwareaopen將小於30 pixels的物體移除
    %移除不必要的雜訊，以免造成分析上的不便
bw = imfill(~bw,'holes');
    %imfill所有被邊界所圍起來的洞填滿，這樣可以估計regionprops

imshow(bw)
figure(4)

%Step4. Find the boundary
[B,L] = bwboundaries(bw,'noholes');

    % Display the label matrix and draw each boundary
imshow(label2rgb(L, @jet, [.5 .5 .5]))
hold on
for k = 1:length(B)
  boundary = B{k};
  plot(boundary(:,2), boundary(:,1), 'w', 'LineWidth', 2)
end

%Circular resolution

