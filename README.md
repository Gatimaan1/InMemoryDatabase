# In-Memory Database

This is my EHAX project. I made a simple key-value database using basic C.

The program starts with an empty database. I can enter commands to set, get, delete, and check data. I can also save the data to a JSON file and load it later using `SAVE` and `LOAD` commands.

In this project, I learned about structures, arrays, pointers, functions, string handling, and file handling in C. I also learned how to use `fprintf()` and `fscanf()` to write data to a file and read it back.

I also learned basic JSON formatting and parsing in C. For example, while saving the database, I used `fprintf()` to write the key-value pairs in JSON format. While loading, I used `fscanf()` to read the keys and values back from the JSON file.

I also implemented basic error handling in the project. For example, if I try to use `GET` or `DEL` with a key that does not exist, the program displays `ERROR: Key not found` instead of causing a problem.