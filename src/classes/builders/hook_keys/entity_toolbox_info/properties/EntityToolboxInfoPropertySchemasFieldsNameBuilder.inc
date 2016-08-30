<?php

/**
 * Class PropertySchemasFieldsNameBuilder
 */
class EntityToolboxInfoPropertySchemasFieldsNameBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'schemas_fields_name',
        'model_class' => 'EntityToolboxInfoPropertySchemasFieldsNameModel',
      ),
      $args
    );
    parent::__construct($args);
  }
}