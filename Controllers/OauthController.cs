using Microsoft.AspNetCore.Mvc;

namespace FORMINFOCore.Controllers
{
    public class OauthController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }
    }
}