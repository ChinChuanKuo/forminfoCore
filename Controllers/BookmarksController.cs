using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class BookmarksController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}