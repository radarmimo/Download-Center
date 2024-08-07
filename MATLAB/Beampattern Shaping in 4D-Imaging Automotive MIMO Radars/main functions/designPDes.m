function PDes = designPDes(theta, thetaDes)

    PDes = zeros(size(theta));

    for i = 1:size(thetaDes, 1)
        
        startPt = thetaDes(i, 1);
        endPt = thetaDes(i, 2);

        PDes(theta >= startPt & theta <= endPt) = 1;
    end

    PDes = PDes(:);
    
end
