using FORMINFOCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace FORMINFOCore.Controllers
{
    public class BookmarksController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}