# POSD2017F Homework

## Homework assignment 5

Please use [the files that were used in course](https://github.com/yccheng66/posd2017f) and copy test header to your repository from this project.

In this assignment, you are required to implement the more complete parser through each test. It will use the interface written in the course. And then, there are few tests will need some new methods of different term class, please follow the description of test, implement each method.

And from this week, we start to run [Mob programming](https://www.google.com.tw/search?q=mob+programming). There will be one or two group in every week until the end of semester, they are required to show the demonstration which how they run the mob programming and how to solve the problem that in the assignment. It needs to do rehearse and prior planning with us. See below to get more detail.


#### Update

  * Fri Nov 03 2017 15:06:12

    The method `args()`, it should return `Term *`, not `Term &`. please correct it in your assignment.

    ```diff
    class Struct {
        public:
          int arity(); // return the number of args (terms)
    -     Term & args(int index); // according to index return the term
    +     Term * args(int index); // according to index return the term
      }
    ```

  * Fri Nov 03 2017 11:55:51
  
    The description of test `TEST_F(ParserTest, ListAsStruct)` is wrong, please correct it in your assignment.

    ```diff
    // Then it should return a Struct which contains two terms.
    // And #arity() of the Struct should be 2.
    // And #symbol() of Struct should return ".(1, [])".
    - // And the first term should be number: "1", the second term should be another Strcut: "[]".
    + // And the first term should be number: "1", the second term should be another List: "[]".
    TEST_F(ParserTest, ListAsStruct) {

    }
    ```
  
  * Thu Nov 02 2017 17:30:46
  
    1. The date of each team has been changed because we skip the week of mid-exam.
    
    2. Some people cannot attend the activity on that week, so we adjust them to other week.
        \
        \
          **Team #2 (11/18)&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Team #3 (11/25)&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Team #1 (11/04)&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Team #9 (01/06)**
        \
        ![Imgur](https://i.imgur.com/nkO111j.png) ![Imgur](https://i.imgur.com/mLcnZIb.png) ![Imgur](https://i.imgur.com/ipW1Gvm.png) ![Imgur](https://i.imgur.com/vgN8huc.png)
        
    3. If you also cannot attend the activity on that week, please email to us before at least one week.
    
    4. ~~About the method: `arity()` and `args()`, sorry for vague explanation. Here is the detail of interface:~~
    
    
#### Assignment requirement

  1. Complete the parser with the description of each test

  2. Implement the new method `arity()`, `args()` in `Struct`.
  
  3. Write the corresponding makefile to generate executable file which named hw5. Note that it is the executable name, not the test file name.
  
  4. Make sure your CI jobs are both passed before deadline.

#### Marks

  You totally have 20 tests in your own, each one is 2 points.
  And TA's test also have 20 tests, each one is 3 points.
  The sum of this homework is 90 points.

#### Deadline

  Thur Nov 9 2017 23:59:59

#### Note

  * Try to read building information in console log and fix the hw problem by yourself as possible as you can.
  
  * If your CI job can not pull your repository, email to us.