<?php

/**
 * Class CallbacksValueBuilder
 */
class CallbacksValueBuilder extends ArrayBuilder {
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, "callbacks", $rawData);
  }
}