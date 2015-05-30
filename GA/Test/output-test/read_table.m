function [ A ] = read_table( path, format, size )
    fileID = fopen(path, 'r');
    A = fscanf(fileID, format, size);
    A = A';
    fclose(fileID);
end

