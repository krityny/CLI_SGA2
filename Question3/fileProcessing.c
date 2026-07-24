#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct Employee
{
    int id;
    char name[20];
    int salary;
};

int main()
{
    int fd;

    struct Employee e1 = {101, "Alina", 5000};
    struct Employee e2 = {102, "Bobby", 8000};
    struct Employee e3 = {102, "Monika", 6000};

    // Create and open file
    fd = open("employee.dat", O_CREAT | O_RDWR | O_TRUNC, 0644);

    // Write records
    write(fd, &e1, sizeof(e1));
    write(fd, &e2, sizeof(e2));
    write(fd, &e3, sizeof(e3));


    printf("Employee records written successfully.\n");

    // Update second record
    struct Employee update = {102, "Rihanna", 6000};

    lseek(fd, sizeof(struct Employee), SEEK_SET);
    write(fd, &update, sizeof(update));

    printf("Second record updated successfully.\n");

    // Read first record
    struct Employee temp;

    lseek(fd, 0, SEEK_SET);
    read(fd, &temp, sizeof(temp));

    printf("\nFirst Record\n");
    printf("ID   : %d\n", temp.id);
    printf("Name : %s\n", temp.name);
    printf("Salary : %d\n", temp.salary);

    // Read second record
    lseek(fd, sizeof(struct Employee), SEEK_SET);
    read(fd, &temp, sizeof(temp));

    printf("\nSecond Record\n");
    printf("ID   : %d\n", temp.id);
    printf("Name : %s\n", temp.name);
    printf("Salary : %d\n", temp.salary);

    lseek(fd, 2 * sizeof(struct Employee), SEEK_SET);
    read(fd, &temp, sizeof(temp));

    printf("\nThird Record\n");
    printf("ID   : %d\n", temp.id);
    printf("Name : %s\n", temp.name);
    printf("Salary : %d\n", temp.salary);

    close(fd);

    printf("\nFile closed successfully.\n");

    return 0;
}