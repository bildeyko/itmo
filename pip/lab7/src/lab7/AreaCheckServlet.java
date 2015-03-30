package lab7;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;

/**
 * Created by bilde_000 on 31.03.2015.
 */
public class AreaCheckServlet extends HttpServlet {
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        long timeout= System.currentTimeMillis();
        response.setContentType("text/html;charset=utf-8");
        response.setLocale(new Locale("ru"));

        Float xVal = Float.parseFloat(request.getParameter("xVal"));
        Float rVal = Float.parseFloat(request.getParameter("rVal"));
        Float yVal = Float.parseFloat(request.getParameter("yVal"));
        System.out.println(xVal);
        Mark mark = new Mark(xVal, yVal);

        Boolean status = checkMark(mark, rVal);

        PrintWriter out = response.getWriter();
        try {
            timeout = System.currentTimeMillis() - timeout;
            out.println(GetPage(mark, rVal, status, timeout));
        } finally {
            out.close();
        }
    }

    private boolean checkMark(Mark mark, Float r) {
        if(mark.x >= 0) {
            if(mark.y <= 0 && mark.y >= mark.x - r) {
                return true;
            }
        } else {
            double radius = Math.sqrt(Math.pow(mark.x,2)+Math.pow(mark.y,2));
            if(mark.y >= 0 && radius <= r/2) {
                return true;
            }
            if(mark.y <= 0 && mark.y >= -r && mark.x >= -r/2) {
                return true;
            }
        }
        return false;
    }

    private String GetPage(Mark mark, Float r, Boolean status, long timeout) {
        String cell;
        if(status)
            cell = "<tr><td class='cell_point'>(" + mark.x + "; " + mark.y + ")</td><td class='cell_res_good'>Belongs</td></tr>";
        else
            cell = "<tr><td class='cell_point'>(" + mark.x + "; " + mark.y + ")</td><td class='cell_res_bad'>Doesn't belong</td></tr>";

        return "<!DOCTYPE html>\n" +
                "<html>\n" +
                "\t<head>\n" +
                "\t\t<meta charset=\"utf-8\"> \n" +
                "\t\t<title>Лабораторная 6</title>\n" +
                "\n" +
                "<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\"/>"+
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
                "<div id=\"result_wrapper\" class=\"inline\">\n" +
                "<p>Results:</p>\n" +
                "<div id=\"table_wrapper\">\n" +
                "<table><tr><th colspan='2'>R = " + r + "</th></tr>" +
                cell +
                "</table>" +
                "<p>Runtime: " + timeout + "ms</p>"+
                "<form id=\"input_form\" action=\"/lab7_war_exploded/lab7\" method=\"GET\">\n" +
                "\t\t\t\t\t\t\t<input type=\"submit\" value=\"Check other data\"/>\n" +
                "\t\t\t\t\t\t</form>" +
                "\t\t\t\t</div>" +
                "\t\t\t</div>\t\n" +
                "\t\t</div>\n" +
                "\t</body>\n" +
                "</html>";
    }
}
