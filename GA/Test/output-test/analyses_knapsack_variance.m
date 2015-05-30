FOLDER = '';
problem = struct('knapsack', [FOLDER 'knapsack/'], ...
                 'salesman', [FOLDER 'salesman/']);
knapsack = struct('name', 'knapsack', ...
                  'folder', [FOLDER 'knapsack/'], ...
                  'test', struct('name', {{'normal', 'variance', 'weight'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance', ...
                      'weight', 'weight'));
                  
% Test - Variance
programacao_dinamica = [char(knapsack.folder) char(knapsack.test.variance) '/dynamic-time-' char(knapsack.name) '.txt']; 
A = read_table(programacao_dinamica, '%d %d %d %d', [4 Inf]);
num_test = 30;
for i = 1:num_test
    algoritmo_genetico = [char(knapsack.folder) char(knapsack.test.variance) '/statistic-' char(knapsack.name) '-test-' int2str(i) '.txt'];
    B = read_table(algoritmo_genetico, '%d %d %f %f', [4 Inf]);

    plot(B(:,1), 'r.'); hold on;
    plot(B(:,2), 'b.');
    plot(B(:,3), 'g.');
    plot(B(:,4), 'y.');
    refline(0, A(1,3)); hold on;
    ylim([0, A(1,3)*1.05]);
    
    legend('Melhor Solução', 'Pior Solução', 'Fitness média', 'Desvio padrão', 'Fitness Desejada', 'Location','southoutside','Orientation','horizontal');
    title('Knapsack - Desvio padrão da Fitness');
    ylabel('Fitness');
    xlabel('Geração');
end
hold off;
print([knapsack.folder 'knapsack-variance-test-100-items'], '-dpng');
algoritmo_genetico = [char(knapsack.folder) char(knapsack.test.variance) '/' char(knapsack.name) '-statistic.txt'];
B = read_table(algoritmo_genetico, '%d %d %f %f', [4 Inf]);
fitness = B(:,1);
average = sum(fitness)/length(fitness);
variance = sum((fitness - average).^2)/length(fitness);
standard_deviation = sqrt(variance);
[average, variance, standard_deviation]




