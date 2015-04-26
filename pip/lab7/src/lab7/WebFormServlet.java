package lab7;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;

/**
 * Created by bilde_000 on 30.03.2015.
 */
public class WebFormServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        PrintWriter out = response.getWriter();

        try {
            out.print(GetPage());
        } finally {
            out.close();
        }
    }

    private String GetPage() {
        return "<!DOCTYPE html>\n" +
                "<html>\n" +
                "\t<head>\n" +
                "\t\t<meta charset=\"utf-8\"> \n" +
                "\t\t<title>Lab 7</title>\n" +
                "\n" +
                "<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\"/>"+
                "<script src=\"js/WebForm.js\"></script>\n"+
                "\t</head>\n" +
                "\t<body>\n" +
                "\n" +
                "\t\t<div id=\"wrapper\">\n" +
                "\t\t\t<div id=\"header\">\n" +
                "\t\t\t\t<p>Nikolay Bildeyko</p>\n" +
                "\t\t\t\t<p>group 2101</p>\n" +
                "\t\t\t\t<p>variant 1121</p>\n" +
                "\t\t\t</div>\n" +
                "\t\t\t<div id=\"center_container\">\n" +
                "\t\t\t\t<div id=\"img_container\" class=\"inline\">\n" +
                "\t\t\t\t\t<img src=\"img/areas.png\">\n" +
                "\t\t\t\t</div>\n" +
                "<div id=\"main_container\" class=\"inline\">\n" +
                "\t\t\t\t\t<form id=\"input_form\" action=\"/lab7_Web/lab7\" onsubmit=\"return validateForm()\" method=\"POST\">\n" +
                "\t\t\t\t\t\t<label>X</label>\n" +
                "\t\t\t\t\t\t<br>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"-2\"/>-2</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"-1.5\"/>-1.5</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"-1\"/>-1</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"-0.5\"/>-0.5</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"0\"/>0</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"0.5\"/>0.5</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"1\"/>1</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"1.5\"/>1.5</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"xVal\" value=\"2\"/>2</label>\n" +
                "\t\t\t\t\t\t<br>\n" +
                "\t\t\t\t\t\t<label>Y</label>\n" +
                "\t\t\t\t\t\t<br>\n" +
                "\t\t\t\t\t\t<input type=\"text\" placeholder=\"-3...3\" name=\"yVal\"/>\n" +
                "\t\t\t\t\t\t<br>\n" +
                "\t\t\t\t\t\t<label>R</label>\n" +
                "\t\t\t\t\t\t<br>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"rVal\" value=\"1\"/>1</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"rVal\" value=\"2\"/>2</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"rVal\" value=\"3\"/>3</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"rVal\" value=\"4\"/>4</label>\n" +
                "\t\t\t\t\t\t<label><input type=\"radio\" name=\"rVal\" value=\"5\"/>5</label>\n" +
                "\t\t\t\t\t\t<br>\n" +
                "\t\t\t\t\t\t<input type=\"submit\" value=\"Submit\"/>\n" +
                "\t\t\t\t\t</form>\n" +
                "<div id=\"error_box\"></div>"+
                "\t\t\t\t</div>" +
                "\t\t\t</div>\t\n" +
                "\t\t</div>\n" +
                "\t</body>\n" +
                "</html>";
    }
}
