FOLDER = '';
problem = struct('salesman', [FOLDER 'salesman/']);
salesman = struct('name', 'salesman', ...
                  'folder', [FOLDER 'salesman/'], ...
                  'test', struct('name', {{'normal', 'variance'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance'));
          
% Test - Generations Development
programacao_dinamica = [char(salesman.folder) char(salesman.test.normal) '/dynamic-time-' char(salesman.name) '.txt']; 
A = read_table(programacao_dinamica, '%d %d %d', [3 Inf]);
for i = 1:16
    algoritmo_genetico = [char(salesman.folder) char(salesman.test.normal) '/statistic-' char(salesman.name) '-test-' int2str(i) '.txt'];
    B = read_table(algoritmo_genetico, '%d %d %f %f', [4 Inf]);

    plot(B(:,1), 'r'); hold on;
    plot(B(:,2));
    plot(B(:,3));
    plot(B(:,4));
    if(A(i,2) > 0)
        refline(0, A(i,2)); hold off;
        legend('Melhor Solução', 'Pior Solução', 'Fitness média', 'Desvio padrão', 'Fitness Desejada', 'Location', 'southoutside', 'Orientation', 'horizontal');
    else
        legend('Melhor Solução', 'Pior Solução', 'Fitness média', 'Desvio padrão', 'Location', 'southoutside', 'Orientation', 'horizontal');
    end
    
    title('Caxeiro Viajante - Evolução da Fitness');
    ylabel('Fitness');
    xlabel('Geração');
    print([salesman.folder 'salesman-generation-evolution-' int2str(i * 10) '-cities'], '-dpng'); 
end



