using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

namespace forminfoCore
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddControllersWithViews();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Home/Error");
                // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
                app.UseHsts();
            }
            app.UseHttpsRedirection();
            app.UseStaticFiles();

            app.UseRouting();

            app.UseAuthorization();

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllerRoute(
                    name: "default",
                    pattern: "{controller=Home}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Bookmarks",
                    pattern: "{controller=Bookmarks}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Code",
                    pattern: "{controller=Code}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Forget",
                    pattern: "{controller=Forget}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Icon",
                    pattern: "{controller=Icon}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Login",
                    pattern: "{controller=Login}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Signup",
                    pattern: "{controller=Signup}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Oauth",
                    pattern: "{controller=Oauth}/{action=Index}");

                endpoints.MapControllerRoute(
                    name: "Proform",
                    pattern: "{controller=Proform}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Protour",
                    pattern: "{controller=Protour}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Formor",
                    pattern: "{controller=Formor}/{action=Index}");
                endpoints.MapControllerRoute(
                    name: "Formcel",
                    pattern: "{controller=Formcel}/{action=Index}");
            });
        }
    }
}
