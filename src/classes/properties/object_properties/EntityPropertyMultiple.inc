<?php

/**
 * Class EntityPropertyMultiple
 */
class EntityPropertyMultiple extends EntityProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_key'       => NULL,
        'default_multiple'  => TRUE,
        'default_callbacks' => array(
          'getter' => DEFAULT_MULTI_VALUE_GETTER,
          'setter' => DEFAULT_MULTI_VALUE_SETTER,
        ),
        'default_value'     => array(
          'bundles' => array()
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}