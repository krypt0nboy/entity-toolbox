<?php

/**
 * Class PropertiesValueBuilderNotFieldable
 */
class EntityToolboxInfoPropertiesBuilderNotFieldable extends EntityToolboxInfoPropertiesBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'required_properties' => array(
          'entity_id',
          'entity_human_name',
          'entity_machine_name',
          'entity_weight',
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}