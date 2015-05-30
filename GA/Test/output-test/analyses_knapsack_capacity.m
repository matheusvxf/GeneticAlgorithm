FOLDER = '';
problem = struct('knapsack', [FOLDER 'knapsack/'], ...
                 'salesman', [FOLDER 'salesman/']);
knapsack = struct('name', 'knapsack', ...
                  'folder', [FOLDER 'knapsack/'], ...
                  'test', struct('name', {{'normal', 'variance', 'weight'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance', ...
                      'weight', 'weight'));

% Test - Knapsack capacity O(nW) - pseudo polynomial behavior of the dynamic
% programming
programacao_dinamica = [char(knapsack.folder) char(knapsack.test.weight) '/dynamic-time-' char(knapsack.name) '.txt']; 
algoritmo_genetico = [char(knapsack.folder) char(knapsack.test.weight) '/genetic-time-' char(knapsack.name) '.txt'];
A = read_table(programacao_dinamica, '%d %d %d %d', [4 Inf]);
B = read_table(algoritmo_genetico, '%d %d %d %d', [4 Inf]);

semilogx(A(:,2), A(:,4) / 1000); hold on;
semilogx(B(:,2), B(:,4) / 1000); hold off;
legend('Programação Dinâmica', 'Algoritmo Genêtico', 'Location','southoutside','Orientation','horizontal')
title('Knapsack - Complexidade Programação Dinâmica vs Algoritmo Genético');
ylabel('tempo(ms)');
xlabel('log(Capacidade da Mochila)');
print([knapsack.folder 'knapsack-weight-test-1000-items'], '-dpng');


