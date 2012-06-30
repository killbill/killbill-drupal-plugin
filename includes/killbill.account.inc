<?php

function killbill_retrieve_account($user) {
    $killbill_account = new Killbill_Account();
    $killbill_account->externalKey = $user->uid;
    return $killbill_account->get();
}