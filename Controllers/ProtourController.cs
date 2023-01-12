using FORMINFOCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace FORMINFOCore.Controllers
{
    public class ProtourController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}