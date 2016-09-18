<?php

/**
 * Class IntegerProperty
 */
class IntegerProperty extends NumericProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'integer',
        'default_php_type'       => 'integer',
        'default_drupal_type'    => 'integer',
      ),
      $args
    );

    parent::__construct($args);
  }
}