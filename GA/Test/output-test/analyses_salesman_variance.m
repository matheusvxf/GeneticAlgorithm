FOLDER = '';
problem = struct('salesman', [FOLDER 'salesman/']);
salesman = struct('name', 'salesman', ...
                  'folder', [FOLDER 'salesman/'], ...
                  'test', struct('name', {{'normal', 'variance'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance'));
                  
% Test - Variance
programacao_dinamica = [char(salesman.folder) char(salesman.test.variance) '/dynamic-time-' char(salesman.name) '.txt']; 
A = read_table(programacao_dinamica, '%d %d %d', [3 Inf]);
num_test = 30;
for i = 1:num_test
    algoritmo_genetico = [char(salesman.folder) char(salesman.test.variance) '/statistic-' char(salesman.name) '-test-' int2str(i) '.txt'];
    B = read_table(algoritmo_genetico, '%d %d %f %f', [4 Inf]);

    plot(B(:,1), 'r.'); hold on;
    plot(B(:,2), 'b.');
    plot(B(:,3), 'g.');
    plot(B(:,4), 'y.');
    refline(0, A(1,2)); hold on;
    
    legend('Melhor Solução', 'Pior Solução', 'Fitness média', 'Desvio padrão', 'Fitness Desejada', 'Location','southoutside','Orientation','horizontal');
    title('Caxeiro Viajante - Desvio Padrão da Fitness');
    ylabel('Fitness');
    xlabel('Geração');
end
hold off;
print([salesman.folder 'salesman-variance-test-100-items'], '-dpng');
algoritmo_genetico = [char(salesman.folder) char(salesman.test.variance) '/' char(salesman.name) '-statistic.txt'];
B = read_table(algoritmo_genetico, '%d %d %f %f', [4 Inf]);
fitness = B(:,1);
average = sum(fitness)/length(fitness);
variance = sum((fitness - average).^2)/length(fitness);
standard_deviation = sqrt(variance);
[average, variance, standard_deviation]




