FOLDER = '';
problem = struct('knapsack', [FOLDER 'knapsack/'], ...
                 'salesman', [FOLDER 'salesman/']);
knapsack = struct('name', 'knapsack', ...
                  'folder', [FOLDER 'knapsack/'], ...
                  'test', struct('name', {{'normal', 'variance', 'weight'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance', ...
                      'weight', 'weight'));
                  
% Test Complexity Number of Items
programacao_dinamica = [char(knapsack.folder) char(knapsack.test.normal) '/dynamic-time-' char(knapsack.name) '.txt']; 
algoritmo_genetico = [char(knapsack.folder) char(knapsack.test.normal) '/genetic-time-' char(knapsack.name) '.txt'];
A = read_table(programacao_dinamica, '%d %d %d %d', [4 Inf]);
B = read_table(algoritmo_genetico, '%d %d %d %d', [4 Inf]);

plot(A(:,1), A(:,4) / 1000); hold on;
plot(B(:,1), B(:,4) / 1000); hold off;
legend('Programação Dinâmica', 'Algoritmo Genêtico')
title('Knapsack - Complexidade Programação Dinâmica vs Algoritmo Genético');
ylabel('tempo(ms)');
xlabel('Número de items');
print([knapsack.folder 'knapsack-num-items-test-capacity-1000'], '-dpng');




