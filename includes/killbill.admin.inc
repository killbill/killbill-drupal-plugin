<?php

function killbill_settings_form($form, &$form_state) {
    $form['account'] = array(
        '#type' => 'fieldset',
        '#title' => t('Default Killbill settings'),
        '#description' => t('Configure these settings based on your Killbill configuration.'),
        '#collapsible' => TRUE,
    );
    $form['account']['killbill_server_url'] = array(
        '#type' => 'textfield',
        '#title' => t('URI'),
        '#description' => t("The absolute URI of the Killbill server, e.g. http://127.0.0.1:8080."),
        '#default_value' => variable_get('killbill_server_url', 'http://127.0.0.1:8080'),
    );

    $form['push'] = array(
        '#type' => 'fieldset',
        '#title' => t('Push notification settings'),
        '#description' => t("Killbill can be configured to send notifications, e.g. when a new account is created or when a subscription event occurs. By default, this open-source module will listen to these " .
                            "notifications to mirror accounts and subscriptions information in your current Drupal database: this is especially useful if you're running a hosted version of Killbill, so all " .
                            "of your critical business data is directly available, without requiring an extra data transfer process." .
                            "Other Drupal modules can also react to incoming push notifications by implementing  hook_killbill_process_push_notification(). This can be useful to extend this module and implement " .
                            "business logic reactions specific to your app." .
                            "Note: if you have supplied an HTTP authentication username and password in your Push Notifications settings in Killbill, your web server must be configured to validate these credentials " .
                            "at your listener URL."),
        '#collapsible' => TRUE,
    );
    $form['push']['killbill_listener_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Listener URL key'),
        '#description' => t('Custom (private) URI to which Killbill will send notifications to.') . '<br />' .
                          t('Based on your current key, you should set @url as your Push Notification URL at Killbill.',
                              array('@url' => url('killbill/listener/' . variable_get('killbill_listener_key', ''), array('absolute' => TRUE)))),
        '#default_value' => variable_get('killbill_listener_key', ''),
        '#required' => TRUE,
        '#size' => 32,
        '#field_prefix' => url('killbill/listener/', array('absolute' => TRUE)),
    );
    $form['push']['killbill_push_logging'] = array(
        '#type' => 'checkbox',
        '#title' => t('Log authenticated incoming push notifications (primarily used for debugging purposes).'),
        '#default_value' => variable_get('killbill_push_logging', FALSE),
    );

    return system_settings_form($form);
}

function killbill_catalog() {
    if (!killbill_client_initialize()) {
        return t('Could not initialize the Killbill client.');
    }

    $catalog = new Killbill_Catalog();
    $catalog->initialize();

    $header = array(t('Product name'), t('Product type'), t('Plan name'), t('Phase type'), t('Price in USD'));
    $rows = array();

    $currency = 'USD';
    foreach ($catalog->getBaseProducts() as $product) {
        foreach ($product->plans as $plan) {
            foreach ($plan->phases as $phase) {
                $rows[] = array(
                    t('@name', array('@name' => $product->name)),
                    t('@type', array('@type' => $product->type)),
                    t('@plan', array('@plan' => $plan->name)),
                    t('@phase', array('@phase' => $phase->type)),
                    t('@price', array('@price' => '$' . number_format($phase->prices->$currency, 2))),
                );
            }
        }
    }

    if (empty($rows)) {
        $rows[] = array(array('data' => t('No catalog found.'), 'colspan' => 5));
    }

    return theme('table', array('header' => $header, 'rows' => $rows));
}