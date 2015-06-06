FOLDER = '';
salesman = struct('name', 'salesman', ...
                  'folder', [FOLDER 'salesman/'], ...
                  'test', struct('name', {{'normal', 'variance'}}, ...
                      'normal', 'normal', ...
                      'variance', 'variance'));
                  
% Test Complexity Number of Cities
programacao_dinamica = [char(salesman.folder) char(salesman.test.normal) '/dynamic-time-' char(salesman.name) '.txt']; 
algoritmo_genetico = [char(salesman.folder) char(salesman.test.normal) '/genetic-time-' char(salesman.name) '.txt'];
A = read_table(programacao_dinamica, '%d %d %d', [3 Inf]);
B = read_table(algoritmo_genetico, '%d %d %d', [3 Inf]);

plot(A(:,1), A(:,3) / 1000); hold on;
plot(B(:,1), B(:,3) / 1000); hold off;
legend('Programação Dinâmica', 'Algoritmo Genêtico', 'Location','southoutside','Orientation','horizontal');
title('Caxeiro Viajante - Complexidade Programação Dinâmica vs Algoritmo Genético');
ylabel('tempo(ms)');
xlabel('Cidades');
print([salesman.folder 'salesman-cidades'], '-dpng');




