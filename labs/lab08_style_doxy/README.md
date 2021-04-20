# Lab 8 - Doxygen

## To Retrieve Class Materials Refer to previous labs.

## We will be grading your remote `master` branch for lab 8  

### Part 1 - Doxygen

Now that your code is Google style compliant, the next part of this lab is to
generate documentation and UML for the code. This is done via Doxygen.

According to their official website,
> Doxygen is the de facto standard tool for generating documentation from
> annotated C++ sources, but it also supports other popular programming languages
> such as C, Objective-C, C#, PHP, Java, Python, IDL (Corba, Microsoft, and
> UNO/OpenOffice flavors), Fortran, VHDL, Tcl, and to some extent D.

Notice how the class PassengerFactory in passenger_factory.h has a description above the
class definition. Doxygen makes use of this to generate documentation for this
class. Doxygen also generates documentation for all functions of a class.

NOTE: Students working on their personal machines will have to download the
doxygen executable before continuing. CSE labs machines already have doxygen
installed.

1. Create the configuration file.

  To start generating documentation, you must first generate a Doxygen
  configuration file in the docs directory. Run the following command from the
  lab08 directory.

  ```
  mkdir docs
  doxygen -g docs/Doxyfile
  ```

  You will now see a new file **Doxyfile** in the docs directory.

2. Modify the Doxyfile to look in the _src_ folder when compiling. You can do
   this by setting the **INPUT** tag of your **Doxyfile** to point to src.

   ```
   ../src
   ```
   Also, to generate the UML, set the **UML_LOOK** and **HAVE_DOT** tag to **YES**.

   The path is relative to the directory from which you run/compile the doxygen. It is important that you set it up to run from docs, because that is where the grading scripts will run from. Doxygen will not inform you if it does not find the src directory -- it just won't generate any files from your classes.

3. Generate the html pages for this lab. Run the following commands:
  ```
  cd docs
  doxygen Doxyfile
  ```

  You can now view the generated documentation from the index.html file in the
  **html** directory that was generated inside the docs folder. Open the index.html page which is refered to as the landing page. Explore the various menus to see how the comments in the code are organized in the html. Click on the classes and you will see UML-like diagrams showing the relationship between classes. One missing piece is a general overview of the code, which you want in the landing page. Currently it is blank because there is no mainpage.h
  file in your src directory.

4. Create a home page for the project. In your _src_ directory, create a file
   **mainpage.h** and paste the following in it.

  ```
  /*! \mainpage My Personal Index Page
   *
   * \section intro_sec Introduction
   *
   * This is the introduction.
   *
   */
 ```

  Generate documentation again by running doxygen as you did before from the
  docs directory and notice how you now have a landing page for your project.

 5. Edit the mainpage.h file by giving it a title and write a
    sentence for the introduction.

 6. Now modify the Passenger.h files to add Doxygen comments and see how that gets added to the documentation. Follow the commenting style that you see in passenger_factory.h. **Use @brief** to describe the class and at least one of the class methods.

   When you have created this documentation (you only need the _.h_
   file), run it again and see how it appears in the class list. Click on the
   class and you will see more detailed information.

7. **Set .gitignore so that you are not pushing the html and latex folders** to your repo. These take a lot of space and can be generated from the Doxygen file, thus there is no need to have them in your repo. You can do this by appending the following entries to your `.gitignore` file:
      - `/docs/html/*`
      - `/docs/latex/*`

 **IMPORTANT**: In future project iterations, proper code style and documentation is worth 50% of the grade. Therefore, it is imperative that you understand how to use both doxygen and style guides!
