﻿using folderCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace folderCore.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
