<?php

/**
 * Class EntityPropertyInfoReferenceMultiplePropertyBuilder
 */
class EntityPropertyInfoReferenceMultiplePropertyBuilder extends EntityPropertyInfoReferencePropertyBuilder {

  /** {{@inheritdoc}} */
  protected function addNumericProperty() {
    $args                   = array(
      'property_name'              => lcfirst($this->propertyName).'_ids',
      'property_type'              => 'list<integer>',
      'key_builder_class'          => 'EntityPropertyInfoReferenceMultipleNumericPropertyBuilder',
      'reference'                  => $this->reference,
      'reference_info'             => $this->referenceInfo,
      'reference_property_builder' => $this,
    );
    $numericPropertyBuilder = $this->getParentBuilder()->addProperty($args);
    $this->__set('numeric_property_builder', $numericPropertyBuilder);
  }
}