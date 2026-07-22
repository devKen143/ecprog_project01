
STUDENT REGISTRAR SYSTEM - APPROACH
=====================================
 
WHAT THIS PROGRAM DOES
-----------------------
A command-line C program that lets a registrar (Dr. Santos) store up to 10
students' records and look them up by ID, GPA threshold, or major, all
within a single running session.
 
 
DATA STORAGE
-------------
Each student's information (ID, name, major, GPA, credits) is grouped into
one struct, "struct Student":
 
    struct Student {
        int id;
        char name[NAME_LEN];
        char major[MAJOR_LEN];
        float gpa;
        int credits;
    };
 
Rather than using five separate parallel arrays (one array of IDs, one of
names, etc.), all of a student's fields live in a single struct. This means:
  - int, char, and float types are all represented, per the assignment.
  - Every value that belongs to one student stays together and moves
    together, which mirrors how Dr. Santos actually thinks about a
    "record" (a folder with one student's info in it, not five separate
    lists she has to keep in sync).
 
The whole system is just one array of these structs:
 
    struct Student students[MAX_STUDENTS];
 
plus an integer "count" that tracks how many of the 10 slots are filled.
This is the array concept applied at the level of whole records instead of
individual numbers.
 
 
PROGRAM FLOW
------------
main() runs a loop that:
  1. Prints a numbered menu.
  2. Reads Dr. Santos's choice with scanf.
  3. Uses a switch statement to call the matching function.
  4. Repeats until she chooses "Exit".
 
This keeps main() short and readable - it's just a dispatcher. All the real
work happens in dedicated functions, one per feature:
 
    addStudent()     - reads a new record from the keyboard and stores it
    displayAll()      - loops over every stored student and prints them
    searchById()       - loops over students, uses an if-match on ID
    searchByGPA()      - loops over students, uses an if-match on GPA >= threshold
    searchByMajor()     - loops over students, uses strcmp to match major, counts matches
    printStudent()      - shared helper that formats one student's line of output
    clearInputBuffer() - helper that discards a leftover newline after scanf("%d"/"%f")
 
Splitting the program this way means each function has exactly one job,
which makes the logic easy to follow and easy to test/change independently
(e.g. changing how a student is displayed only touches printStudent()).
 
 
WHY fgets() FOR NAME AND MAJOR
--------------------------------
scanf("%s", ...) stops reading at the first space, so "Alice Johnson" or
"Computer Science" would get cut off after the first word. fgets() reads a
full line instead, so multi-word names and majors are captured correctly.
The trailing newline that fgets() keeps is then stripped with:
 
    s.name[strcspn(s.name, "\n")] = '\0';
 
WHY clearInputBuffer()
------------------------
scanf("%d", ...) and scanf("%f", ...) leave the newline character in the
input buffer after reading a number. If the next read is fgets() for a
name, it would immediately read that leftover blank line instead of
waiting for real input. clearInputBuffer() throws away everything up to
and including that newline so the next prompt behaves as expected.
 
 
SEARCH LOGIC
-------------
All three search functions use the same basic pattern - a for loop over
the filled portion of the array, with an if statement inside to test the
condition:
 
  - searchById:    if (students[i].id == targetId)          -> exact match, stop after first hit (IDs are unique)
  - searchByGPA:    if (students[i].gpa >= threshold)         -> collect every match, keep a running count
  - searchByMajor:  if (strcmp(students[i].major, target) == 0) -> string comparison, collect every match, print total count
 
Strings can't be compared with == in C (that would compare memory
addresses, not contents), so strcmp() is used for the major search;
numbers can be compared directly with == or >=.
 
 
LIMITS AND EDGE CASES HANDLED
-------------------------------
- Adding a student when the array is already full (10/10) prints a message
  instead of writing past the end of the array.
- Searching when there are zero students yet prints "No students on file"
  rather than silently doing nothing.
- A GPA search or major search with no matches reports that clearly instead
  of leaving Dr. Santos wondering if the program worked.
- Invalid menu input (e.g. typing a letter instead of a number) is caught
  and the buffer is cleared so the program doesn't get stuck in a loop.
 
 
WHAT WOULD COME NEXT (OUT OF SCOPE FOR NOW)
----------------------------------------------
- Saving/loading records to a file so data survives after the program closes.
- Editing or deleting an existing student record.
- Case-insensitive major search.
- Sorting the display (by name, GPA, or ID).
 
These weren't required by the current success metrics, so they were left
out to keep the program focused on the five core features.
