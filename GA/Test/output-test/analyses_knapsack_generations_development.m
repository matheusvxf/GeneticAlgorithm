FOLDER = '';
problem = struct('knapsack', [FOLDER 'knapsack/'], ...
                 'salesman', [FOLDER 'salesman/']);
knapsack = struct('name', 'knapsack', ...
                  'folder', [FOLDER 'knapsack/'], ...
                  'test', struct('name', {{'normal', 'variance', 'weight'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance', ...
                      'weight', 'weight'));
          
% Test - Generations Development
programacao_dinamica = [char(knapsack.folder) char(knapsack.test.normal) '/dynamic-time-' char(knapsack.name) '.txt']; 
A = read_table(programacao_dinamica, '%d %d %d %d', [4 Inf]);
for i = 1:20
    algoritmo_genetico = [char(knapsack.folder) char(knapsack.test.normal) '/statistic-' char(knapsack.name) '-test-' int2str(i) '.txt'];
    B = read_table(algoritmo_genetico, '%d %d %f %f', [4 Inf]);

    plot(B(:,1), 'r'); hold on;
    plot(B(:,2));
    plot(B(:,3));
    plot(B(:,4));
    refline(0, A(i,3)); hold off;
    ylim([0, A(i,3)*1.05]);
    
    legend('Melhor Solução', 'Pior Solução', 'Fitness média', 'Desvio padrão', 'Fitness Desejada', 'Location','southoutside','Orientation','horizontal');
    title('Knapsack - Evolução da Fitness');
    ylabel('Fitness');
    xlabel('Geração');
    print([knapsack.folder 'knapsack-generation-evolution-normal-test-' int2str(i * 10) '-items'], '-dpng'); 
end



