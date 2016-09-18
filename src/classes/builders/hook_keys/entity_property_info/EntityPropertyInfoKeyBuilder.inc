<?php

/**
 * Class EntityPropertyInfoValueBuilder
 */
class EntityPropertyInfoKeyBuilder extends EntityToolboxDependentHookKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'entity_property_info'
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function validateStringValue($value, $valueType) {
    if ($this->isValueTemplate($value)) {
      return NULL;
    }
    else {
      return $value;
    }
  }

}