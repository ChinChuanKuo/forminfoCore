using folderCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace folderCore.Controllers
{
    public class BookmarksController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}