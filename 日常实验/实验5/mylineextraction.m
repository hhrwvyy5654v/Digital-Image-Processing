function [bp, ep] = mylineextraction(BW)
    %   The function extracts the longest line segment from the given binary image
    %       Input parameter:
    %       BW = A binary image.
    %
    %       Output parameters:
    %       [bp, ep] = beginning and end points of the longest line found
    %       in the image.
    [n, m] = size(BW);
    [H,T,R] = hough(BW);
    P  = houghpeaks(H,8,'threshold',ceil(0.2*max(H(:))));
    lines= houghlines(BW,T,R,P,'FillGap',20,'MinLength',7);
    maxLength = 0;
    for k = 1:length(lines)  
        xy = [lines(k).point1; lines(k).point2];
        if (((xy(1,1) - xy(2,1))^2 + (xy(1,2) - xy(2,2))^2) > maxLength) 
            maxLength = (xy(1,1) - xy(2,1))^2 + (xy(1,2) - xy(2,2))^2;
            bp = xy(1,:);
            ep = xy(2,:);
        end
    end  