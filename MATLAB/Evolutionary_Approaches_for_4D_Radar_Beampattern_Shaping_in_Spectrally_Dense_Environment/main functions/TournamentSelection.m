function i = TournamentSelection(pop,m)

    nPop = numel(pop);

    S = randsample(nPop,m);
    
    spop = pop(S);
    
    scosts = [spop.Cost];
    
    [~, j] = min(scosts);
    
    i = S(j);

end