using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class ProtourController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}