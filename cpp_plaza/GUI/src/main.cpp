/*
** main.cpp for cpp_plaza in /home/kleinh/Documents/TEK2/cpp_plaza/GUI/src/main.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Thu Apr 20 13:05:12 2017 Arthur Klein
** Last update Thu Apr 20 13:05:12 2017 Arthur Klein
*/

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/filebox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <experimental/filesystem>
#include <iostream>

int main()
{
  //Define a form.
  const		nana::point pt(300,200);
  std::string	str("Hello, welcome to the cpp_plaza's project !");
  nana::form fm(nana::API::make_center(600, 300));
  nana::form fm_file(nana::API::make_center(600, 300));
  nana::label lab(fm, nana::rectangle(180, 10, str.size() * 10, 40));
  nana::button btn(fm, nana::rectangle(nana::point(200, 200), nana::size(100, 25)));
  nana::button btn_success(fm, nana::rectangle(nana::point(300, 200), nana::size(100, 25)));

  lab.caption(str);
  fm.collocate();
  fm.show();
  btn.caption("Exit");
  btn_success.caption("See the file");
  btn.events().click([&fm] {
    fm.close();
  });
  //Define a label and display a text.
  lab.format(true);

  btn_success.events().click([&fm] {
    fm.close();
    nana::filebox fb(0, true);
    fb.add_filter(("Text File"), ("*.text;*.doc"));
    fb.add_filter(("All Files"), ("*.*"));
    if (fb())
    {
      std::string file = fb.file();
      std::cout << "Selected file:  " << file << std::endl;
    }
  });
  nana::exec();
}
