import "../sibawa.ini"

CheckPrivilege "admin"

cgi::Header 200,"text/html"
cgi::FinishHeader

PrintTemplate("admin/newuser.html")

stop
end