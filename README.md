killbill-drupal-plugin
======================

Drupal module for Killbill. Tested on Drupal 7 only.

Getting started
---------------

Please refer to the [Drupal documentation](http://drupal.org/start) for the Drupal specific steps.
The ones below should work for a standard Apache/MySQL insteallation on Mac OS X or Linux.

1. Create a MySQL account and database
    1. `create database drupal;`
    2. `create user 'drupal'@'localhost' identified by 'drupal';`
    3. `grant all on drupal.* to 'drupal'@'localhost';`
2. Prepare Apache to serve the Drupal installation, e.g.
<pre>&lt;Directory "/opt/drupal"&gt;
        Options Indexes MultiViews FollowSymLinks
        AllowOverride All
        Order deny,allow
        Deny from all
        Allow from 127.0.0.1 localhost
    &lt;/Directory&gt;
</pre>
3. Install Drupal 7
    1. Download Drupal by going to http://drupal.org/project/drupal
    2. Unpack the zip or tarball under `/opt/drupal`
    3. In the drupal directory, add the default files directory
        1. `mkdir -p sites/default/files`
        2. `chmod o+w sites/default/files/`
    4. Create the configuration file
        1. `cp ./sites/default/default.settings.php ./sites/default/settings.php`
        2. Configure the MySQL driver by adding right after `databases = array();`:
<pre>$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => 'drupal',
  'username' => 'drupal',
  'password' => 'drupal',
  'host' => 'localhost',
  'prefix' => '',
);
</pre>
    5. Go to http://127.0.0.1 and follow the instructions
4. Install the libraries modules
    1. Download the module [here](http://drupal.org/project/libraries/)
    2. Unzip it in the `/sites/all/modules` directory
    3. Enable it by going to http://127.0.0.1/admin/modules
5. Install the Killbill module
    1. Download the module [here](https://github.com/killbilling/killbill-drupal-plugin/zipball/master)
    2. Unzip it in the `/sites/all/modules` directory
    3. Enable it by going to http://127.0.0.1/admin/modules
6. Configure the Killbill module
    1. Configure the permissions by going to http://127.0.0.1/admin/people/permissions#module-killbill
    2. Configure your Killbill installation by going to http://127.0.0.1:90/admin/config/services/killbill
7. Verify your installation
    1. Create a new user in your Drupal installation by going to http://127.0.0.1/user/register (logout as admin first)
    2. Log back in as admin and find your newly created user by going to http://127.0.0.1/admin/people
    3. Click on his username and should should see a *Killbill information* section in the user details page
8. Congrats! You're all set!